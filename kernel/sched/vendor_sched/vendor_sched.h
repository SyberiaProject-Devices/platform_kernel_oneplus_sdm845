/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _VH_SCHED_H
#define _VH_SCHED_H

#define ANDROID_VENDOR_CHECK_SIZE_ALIGN(_orig, _new)				\
		static_assert(sizeof(struct{_new;}) <= sizeof(struct{_orig;}),	\
			       __FILE__ ":" __stringify(__LINE__) ": "		\
			       __stringify(_new)				\
			       " is larger than "				\
			       __stringify(_orig) );				\
		static_assert(__alignof__(struct{_new;}) <= __alignof__(struct{_orig;}),	\
			       __FILE__ ":" __stringify(__LINE__) ": "		\
			       __stringify(_orig)				\
			       " is not aligned the same as "			\
			       __stringify(_new) );

// Maximum size: u64[2] for ANDROID_VENDOR_DATA_ARRAY(1, 2) in task_struct

void find_energy_efficient_cpu_pixel_mod(struct task_struct *p, int prev_cpu,
                                    int sync, int *new_cpu);

void rvh_set_iowait(struct task_struct *p, int *should_iowait_boost);

void rvh_cpu_overutilized(int cpu, int *overutilized);

void rvh_dequeue_task(struct rq *rq, struct task_struct *p, int flags);

void rvh_uclamp_eff_get(struct task_struct *p, enum uclamp_id clamp_id,
			  struct uclamp_se *uclamp_max, struct uclamp_se *uclamp_eff,
			  int *ret);

void rvh_util_est_update(struct cfs_rq *cfs_rq, struct task_struct *p,
			    bool task_sleep, int *ret);

void rvh_post_init_entity_util_avg(struct sched_entity *se);

void rvh_check_preempt_wakeup(struct rq *rq, struct task_struct *p,
			bool *preempt, bool *nopreempt, int wake_flags, struct sched_entity *se,
			struct sched_entity *pse, int next_buddy_marked, unsigned int granularity);

void rvh_cpu_cgroup_online(struct cgroup_subsys_state *css);

void rvh_sched_fork(struct task_struct *p);

unsigned long schedutil_cpu_util_pixel_mod(int cpu, unsigned long util_cfs,
	 unsigned long max, enum cpu_util_type type,
	 struct task_struct *p);

unsigned long map_util_freq_pixel_mod(unsigned long util, unsigned long freq,
		      unsigned long cap, int cpu);

enum vendor_group {
	VG_SYSTEM=0,
	VG_TOPAPP,
	VG_FOREGROUND,
	VG_CAMERA,
	VG_CAMERA_POWER,
	VG_BACKGROUND,
	VG_SYSTEM_BACKGROUND,
	VG_NNAPI_HAL,
	VG_RT,
	VG_DEX2OAT,
	VG_SF,
	VG_MAX,
};

struct vendor_task_struct {
	enum vendor_group group;
	unsigned long direct_reclaim_ts;
	bool uclamp_fork_reset;
};

ANDROID_VENDOR_CHECK_SIZE_ALIGN(u64 android_vendor_data1[64], struct vendor_task_struct t);

static inline struct vendor_task_struct *get_vendor_task_struct(struct task_struct *p)
{
	return (struct vendor_task_struct*)p->android_vendor_data1;
}

#endif
