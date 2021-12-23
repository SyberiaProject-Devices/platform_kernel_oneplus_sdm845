// SPDX-License-Identifier: GPL-2.0-only
/* init.c
 *
 * Android Vendor Hook Support
 *
 * Copyright 2020 Google LLC
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cpufreq.h>
#include <trace/hooks/sched.h>
#include <trace/hooks/topology.h>

extern int create_sysfs_node(void);
extern void rvh_find_energy_efficient_cpu_pixel_mod(void *data, struct task_struct *p, int prev_cpu,
			    int sync, int *new_cpu);
extern void vh_arch_set_freq_scale_pixel_mod(void *data,
		         const struct cpumask *cpus,
		         unsigned long freq,
		         unsigned long max,
		         unsigned long *scale);
extern void vh_set_sugov_sched_attr_pixel_mod(void *data, struct sched_attr *attr);
extern void rvh_set_iowait_pixel_mod(void *data, struct task_struct *p, int *should_iowait_boost);
extern void rvh_select_task_rq_rt_pixel_mod(void *data, struct task_struct *p, int prev_cpu,
		        int sd_flag, int wake_flags, int *new_cpu);
extern void rvh_cpu_overutilized_pixel_mod(void *data, int cpu, int *overutilized);
extern void rvh_dequeue_task_pixel_mod(void *data, struct rq *rq, struct task_struct *p, int flags);
extern void rvh_uclamp_eff_get_pixel_mod(void *data, struct task_struct *p,
		     enum uclamp_id clamp_id, struct uclamp_se *uclamp_max,
		     struct uclamp_se *uclamp_eff, int *ret);
extern void rvh_util_est_update_pixel_mod(void *data, struct cfs_rq *cfs_rq, struct task_struct *p,
		       bool task_sleep, int *ret);
extern void rvh_post_init_entity_util_avg_pixel_mod(void *data, struct sched_entity *se);
extern void rvh_check_preempt_wakeup_pixel_mod(void *data, struct rq *rq, struct task_struct *p,
	    bool *preempt, bool *nopreempt, int wake_flags, struct sched_entity *se,
	    struct sched_entity *pse, int next_buddy_marked, unsigned int granularity);
extern void rvh_cpu_cgroup_online_pixel_mod(void *data, struct cgroup_subsys_state *css);
extern void vh_sched_setscheduler_uclamp_pixel_mod(void *data, struct task_struct *tsk,
			   int clamp_id, unsigned int value);
extern void init_uclamp_stats(void);
extern void rvh_sched_fork_pixel_mod(void *data, struct task_struct *tsk);

extern void vh_sched_setscheduler_uclamp_pixel_mod(void *data, struct task_struct *tsk,
						   int clamp_id, unsigned int value);

extern struct cpufreq_governor sched_pixel_gov;

static int vh_sched_init(void)
{
	int ret;
	pr_info("Starting vendor_sched hooks...");
	ret = create_sysfs_node();
	if (ret) {
		pr_err("Failed to create sysfs nodes.");
		return ret;
	}

	pr_info("vendor_sched: Adding hook for find_energy_efficient_cpu...");
	ret = register_trace_android_rvh_find_energy_efficient_cpu(
						rvh_find_energy_efficient_cpu_pixel_mod, NULL);
	if (ret) {
		pr_err("Failed to install hook.");
		return ret;
	}

	pr_info("vendor_sched: Adding hook for arch_set_freq_scale...");
	ret = register_trace_android_vh_arch_set_freq_scale(vh_arch_set_freq_scale_pixel_mod, NULL);
	if (ret) {
		pr_err("Failed to install hook.");
		return ret;
	}

	pr_info("vendor_sched: Adding hook for set_iowait...");
	ret = register_trace_android_rvh_set_iowait(rvh_set_iowait_pixel_mod, NULL);
	if (ret) {
		pr_err("Failed to install hook.");
		return ret;
	}

	pr_info("vendor_sched: Adding hook for select_task_rq_rt...");
	ret = register_trace_android_rvh_select_task_rq_rt(rvh_select_task_rq_rt_pixel_mod, NULL);
	if (ret) {
		pr_err("Failed to install hook.");
		return ret;
	}

	pr_info("vendor_sched: Adding hook for cpu_overutilized...");
	ret = register_trace_android_rvh_cpu_overutilized(rvh_cpu_overutilized_pixel_mod, NULL);
	if (ret) {
		pr_err("Failed to install hook.");
		return ret;
	}

	pr_info("vendor_sched: Adding hook for dequeue_task...");
	ret = register_trace_android_rvh_dequeue_task(rvh_dequeue_task_pixel_mod, NULL);
	if (ret) {
		pr_err("Failed to install hook.");
		return ret;
	}

	pr_info("vendor_sched: Adding hook for util_est_update...");
	ret = register_trace_android_rvh_util_est_update(rvh_util_est_update_pixel_mod, NULL);
	if (ret) {
		pr_err("Failed to install hook.");
		return ret;
	}

	pr_info("vendor_sched: Adding hook for uclamp_eff_get...");
	ret = register_trace_android_rvh_uclamp_eff_get(rvh_uclamp_eff_get_pixel_mod, NULL);
	if (ret) {
		pr_err("Failed to install hook.");
		return ret;
	}

	pr_info("vendor_sched: Adding hook for post_init_entity_util_avg...");
	ret = register_trace_android_rvh_post_init_entity_util_avg(
		rvh_post_init_entity_util_avg_pixel_mod, NULL);
	if (ret) {
		pr_err("Failed to install hook.");
		return ret;
	}

	pr_info("vendor_sched: Adding hook for check_preempt_wakeup...");
	ret = register_trace_android_rvh_check_preempt_wakeup(
		rvh_check_preempt_wakeup_pixel_mod, NULL);
	if (ret) {
		pr_err("Failed to install hook.");
		return ret;
	}

	pr_info("vendor_sched: Adding hook for cpu_cgroup_online...");
	ret = register_trace_android_rvh_cpu_cgroup_online(
		rvh_cpu_cgroup_online_pixel_mod, NULL);
	if (ret) {
		pr_err("Failed to install hook.");
		return ret;
	}

	pr_info("vendor_sched: Adding hook for setscheduler_uclamp...");
	ret = register_trace_android_vh_setscheduler_uclamp(
		vh_sched_setscheduler_uclamp_pixel_mod, NULL);
	if (ret) {
		pr_err("Failed to install hook.");
		return ret;
	}

	pr_info("vendor_sched: Adding hook for sched_fork...");
	ret = register_trace_android_rvh_sched_fork(rvh_sched_fork_pixel_mod, NULL);
	if (ret) {
		pr_err("Failed to install hook.");
		return ret;
	}


	pr_info("vendor_sched: Registering pixed_sched governor...");
	ret = cpufreq_register_governor(&sched_pixel_gov);
	if (ret)
		return ret;

	pr_info("Vendor_sched hooks successfully installed!");
	return 0;
}

module_init(vh_sched_init);
MODULE_LICENSE("GPL v2");
