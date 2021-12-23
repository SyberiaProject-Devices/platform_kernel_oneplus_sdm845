// SPDX-License-Identifier: GPL-2.0-only
/* vendor_hook.c
 *
 * Android Vendor Hook Support
 *
 * Copyright (C) 2020 Google, Inc.
 */

#define CREATE_TRACE_POINTS
#include <trace/hooks/vendor_hooks.h>
#include <trace/hooks/sched.h>
#include <trace/hooks/topology.h>

/*
 * Export tracepoints that act as a bare tracehook (ie: have no trace event
 * associated with them) to allow external modules to probe them.
 */

EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_cpu_cgroup_online);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_select_task_rq_rt);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_dequeue_task);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_find_energy_efficient_cpu);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_set_iowait);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_post_init_entity_util_avg);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_check_preempt_wakeup);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_sched_fork);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_cpu_overutilized);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_util_est_update);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_setscheduler_uclamp);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_uclamp_eff_get);
